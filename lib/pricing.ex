 defmodule Pricing do

   @doc "
   Usage:

   def option(opts \\ []) do
     [price: p, strike: k, rate: r, t: t, vol: v, dy: d] = opts
     ...
   end
   "
  def run_pricing_binary_with_inputs(opts \\ []) do
    [price: p, strike: k, rate: r, t: t, vol: v, dy: d] = opts
    %Porcelain.Result{err: _err, out: out} = Porcelain.exec("./pricing.x", [p, k, r, t, v, d])
    out
  end

  def price(opts \\ []) do
    price_option_with_inputs(opts)
  end

  def price_option_with_inputs(opts \\ []) do
    [price: p, strike: k, rate: r, t: t, vol: v, dy: d] = opts
    price = :erlang.float_to_binary(p) # 2168
    strike = :erlang.float_to_binary(k) # 2200
    rate = :erlang.float_to_binary(r, [decimals: 3]) # 0.0025
    t = :erlang.float_to_binary(t, [decimals: 2]) # 0.0904
    v = :erlang.float_to_binary(v, [decimals: 2]) # 0.95
    dy = :erlang.float_to_binary(d, [decimals: 2]) # 0.001

    components = [
      price: price,
      strike: strike,
      rate: rate,
      t: t,
      vol: v,
      dy: dy
    ]
     %{"call" => call, "put" => put} =
       Poison.decode!(Pricing.run_pricing_binary_with_inputs(components))

     [call: call, put: put]
     |> Enum.into(%{})
   end

   @doc "
    Pricing.price([price: 2450.94, strike: 2650.0, rate: 0.01125, t: 0.083, vol: 2.4, dy: 0.0])
   "
   def test do
     Pricing.price([price: 435.25, strike: 434.0, rate: 0.0125, t: 0.02556, vol: 0.175, dy: 0.07])
   end
end
