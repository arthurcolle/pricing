defmodule Pricing do
	use Timex
	
	def option(opts) do
		[price: price, strike: strike, risk_free_rate: rate, time_to_expiry: time, volatility: vol, dividend_yield: d] = opts
		args = opts
		%Porcelain.Result{err: err, out: out} = 
		"./pricing.exe"
		|> Porcelain.exec([price, strike, rate, time, vol, d])
		IO.puts out
	end

	def btc do
		%Timex.DateTime{ms: start} = Date.now()		
		Pricing.option([	
			price: "400", 
			strike: "250", 
			risk_free_rate: "0.005", 
			time_to_expiry: "1.00", 
			volatility: "0.7", 
			dividend_yield: "0.00"
		]) 
		%Timex.DateTime{ms: nd} = Date.now()
		IO.puts(nd-start)
	end
end
