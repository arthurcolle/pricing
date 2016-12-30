defprotocol Priceable do
	@doc "Returns a price if data needed for pricing is present"
	def price(data)
end