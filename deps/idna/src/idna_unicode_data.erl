-module(idna_unicode_data).

-export([combining_class/1,
         compat/1,
         composition/2,
         lowercase/1]).

-define(COMBINING_CLASS, 1).
-define(DECOMPOSITION, 2).
-define(LOWERCASE_MAPPING, 3).

combining_class(C) ->
    case lookup(C) of
        false -> 0;
        Props ->
            erlang:list_to_integer(element(?COMBINING_CLASS, Props))
    end.

compat(C) ->
    lookup(C, fun(Props) ->
                case element(?DECOMPOSITION, Props) of
                    [] -> undefined;
                    Val ->
                        Tokens = string:tokens(Val, " "),
                        CodePoints = dehex(case hd(Val) of
                                    $< -> tl(Tokens);
                                    _ -> Tokens
                                end),
                        CodePoints
                end
        end).

composition(A, B) ->
    Key = lists:flatten([hex(A), " ", hex(B)]),
    case idna_unicode_data1:decomposition(Key) of
        false -> undefined;
        Val -> erlang:list_to_integer(Val, 16)
    end.


lowercase(C) ->
    lookup(C, fun(Props) ->
                case element(?LOWERCASE_MAPPING, Props) of
                    [] -> C;
                    Hex -> erlang:list_to_integer(Hex, 16)
                end
        end).

%% --------------------
%% helper functions
%% --------------------

hex(Codepoint) ->
  string:right(erlang:integer_to_list(Codepoint, 16), 4, $0).

dehex(Strings) ->
  [erlang:list_to_integer(String, 16) || String <- Strings].

lookup(Codepoint) ->
    idna_unicode_data2:lookup1(hex(Codepoint)).

lookup(Codepoint, Fun) ->
    case lookup(Codepoint) of
        false -> {error, bad_codepoint};
        Props -> Fun(Props)
    end.


-ifdef(TEST).

-include_lib("eunit/include/eunit.hrl").

fixture_path(Name) ->
    EbinDir = filename:dirname(code:which(?MODULE)),
    AppPath = filename:dirname(EbinDir),
    filename:join([AppPath, "test", Name]).


punycode_encode_test() ->
    test_each(fixture_path("punycode_*"), fun (Test) ->
                                                  Expect = proplists:get_value(punycode, Test),
                                                  Input =proplists:get_value(unicode, Test),
                                                  ?assertEqual(Expect, punycode:encode(Input))
                                          end).

idna_to_ascii_test() ->
    test_each("test/idna_*", fun (Test) ->
                                     Expect = proplists:get_value(output, Test),
                                     Input = proplists:get_value(input, Test),
                                     ?assertEqual(Expect,idna:to_ascii(idna_ucs:from_utf8(Input)))
                             end).

test_each(FilePattern, Fun) ->
    test_each1(filelib:wildcard(FilePattern), Fun).

test_each1([], _) ->
    ok;
test_each1([File | Files], Fun) ->
    {ok, Test} = file:consult(File),
    Fun(Test),
    test_each1(Files, Fun).

-endif.
