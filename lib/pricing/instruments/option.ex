defmodule EuropeanOption do
	use Timex

  defstruct [
    type: :european,
    strike: 100.0,
    expiry: Date.now()
  ]

  def price( option, opts \\ [] ) do
    0
  end
end
