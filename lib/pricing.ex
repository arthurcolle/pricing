defmodule Pricing do
	def option(opts \\ []) do
		args = opts
		%Porcelain.Result{err: err, out: out} = 
			Porcelain.exec("./pricing.exe", args)
		IO.puts out
	end

	def example do
		Pricing.option ["250", "520", "0.005", "5.00", "0.2", "0.00"]
	end
end
