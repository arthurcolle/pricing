# Pricing

**TODO: Read in parameters for pricing formula from stdin**
**TODO: American options**

```
iex(2)> Pricing.btc
{s: 400.000000,k: 250.000000,r: 0.005000,t: 1.000000,v: 0.700000,d: 0.000000,prices: ["c":178.268061, "p":27.021181]}

12           # this is how many milliseconds the call down to the C binary took
:ok
```



## Installation

If [available in Hex](https://hex.pm/docs/publish), the package can be installed as:

  1. Add pricing to your list of dependencies in `mix.exs`:

        def deps do
          [{:pricing, "~> 0.0.1"}]
        end

  2. Ensure pricing is started before your application:

        def application do
          [applications: [:pricing]]
        end


To compile the pricing.c file for now just execute the following on the cygwin terminal, thank 

```
		gcc -Wall -I/usr/local/include -c pricing.c
		g++ -L/usr/local/lib/ pricing.o -lgsl -lgslcblas -lm
		./a.exe
```
Expected output:

```
		Underlier price: 87.500000
		   Strike price: 85.000000
		 risk free rate: 0.00500
		 Time to expiry: 0.04000
		     Volatility: 0.06000
		  Discount rate: 0.00000

		price call: 2.519551
		price  put: 0.002552
```
