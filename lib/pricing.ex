defmodule Pricing do
	def option(opts \\ []) do
		[price: p, strike: k, rate: r, t: t, vol: v, dy: d] = opts
		%Porcelain.Result{err: err, out: out} = Porcelain.exec("./pricing.exe", [p, k, r, t, v, d])
		out
	end

	def bitcoin_option do
		price = Integer.to_string(300)
		strike = Integer.to_string(250)
		rate = Float.to_string(0.005, [decimals: 3, compact: true])
		t = Float.to_string(0.75, [decimals: 2, compact: true])
		v = Float.to_string(0.75, [decimals: 2, compact: true])
		dy = Float.to_string(0.001, [decimals: 2, compact: true])

		components = 
			[{:price, price},
			 {:strike, strike}, 
			 {:rate, rate},
       {:t, t},
       {:vol, v}, 
       {:dy, dy}]

		[c,p] = Poison.decode!(Pricing.option(components))
		%{call: c, put: p}
	end
end