defmodule Pricing do
	def option(opts \\ []) do
		[price: p, strike: k, rate: r, t: t, vol: v, dividend_yield: d] = opts
		%Porcelain.Result{err: err, out: out} = Porcelain.exec("./pricing.exe", [p, k, r, t, v, d])
		out
	end

	def bitcoin do
		price = Integer.to_string(300)
		strike = Integer.to_string(250)
		rate = Float.to_string(0.005, [decimals: 3, compact: true])
		t = Float.to_string(0.75, [decimals: 2, compact: true])
		v = Float.to_string(0.75, [decimals: 2, compact: true])
		dy = Float.to_string(0.00, [decimals: 2, compact: true])

		Pricing.option([	
			price: price,
			strike: strike, 
			rate: rate,
			t: t,
			vol: v, 
			dividend_yield: dy
		]) 
	end
end


[price: 123, x: 119]