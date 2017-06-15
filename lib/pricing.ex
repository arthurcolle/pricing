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
    %Porcelain.Result{err: err, out: out} = Porcelain.exec("./pricing.x", [p, k, r, t, v, d])
    out
  end

  def price(opts \\ []) do
    price_option_with_inputs(opts)
  end

  def price_option_with_inputs(opts \\ []) do
    [price: p, strike: k, rate: r, t: t, vol: v, dy: d] = opts
    price = Float.to_string(p) # 2168
    strike = Float.to_string(k) # 2200
    rate = Float.to_string(r, [decimals: 3, compact: true]) # 0.0025
    t = Float.to_string(t, [decimals: 2, compact: true]) # 0.0904
    v = Float.to_string(v, [decimals: 2, compact: true]) # 0.95
    dy = Float.to_string(d, [decimals: 2, compact: true]) # 0.001

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
     Pricing.price([price: 129.94, strike: 135.0, rate: 0.01125, t: 0.083, vol: 2.4, dy: 0.0])
   end
end
