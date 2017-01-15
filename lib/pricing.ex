 defmodule Pricing do
  def option(opts \\ []) do
    [price: p, strike: k, rate: r, t: t, vol: v, dy: d] = opts
    %Porcelain.Result{err: err, out: out} = Porcelain.exec("./pricing.x", [p, k, r, t, v, d])
    out
  end

  def bitcoin_option_test do
    price = Integer.to_string(300)
    strike = Integer.to_string(250)
    rate = Float.to_string(0.005, [decimals: 3, compact: true])
    t = Float.to_string(0.75, [decimals: 2, compact: true])
    v = Float.to_string(0.75, [decimals: 2, compact: true])
    dy = Float.to_string(0.001, [decimals: 2, compact: true])

    components = [
      price: price,
      strike: strike,
      rate: rate,
      t: t,
      vol: v,
      dy: dy
    ]

     %{"call" => call, "put" => put} =
       Poison.decode!(Pricing.option(components))

     [call: call, put: put]
     |> Enum.into(%{})
   end

   def test do
     Pricing.bitcoin_option_test
   end
end
