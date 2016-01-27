# Pricing

**TODO: Read in parameters for pricing formula from stdin**

**TODO: American options**
 
```
 Porcelain.exec("./pricing", ["150 100 0.005 5 0.04 0.00"])
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