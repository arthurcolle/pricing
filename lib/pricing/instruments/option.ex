defmodule Option do
	defstruct [
    type: :european, 
    strike: 100.0,
    expiry: "?"
  ]

  def price( option, opts \\ [] ) do
    0
  end
end