defmodule PricingTest do
  use ExUnit.Case
  doctest Pricing

  test "the truth" do
    assert 1 + 1 == 2
  end

  test "basic option pricing test" do
    price  = Integer.to_string(300)
    strike = Integer.to_string(250)
    rate   = Float.to_string(0.005, [decimals: 3, compact: true])
    t      = Float.to_string(0.75,  [decimals: 2, compact: true])
    v      = Float.to_string(0.75,  [decimals: 2, compact: true])
    dy     = Float.to_string(0.001, [decimals: 2, compact: true])

    components = [
      price: price
      strike: strike,
      rate: rate,
      t: t,
      vol: v,
      dy: dy
    ]

    assert Pricing.option(components) == %{call: 94.586636, put: 43.650892}
  end
end
