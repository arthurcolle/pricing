#!/usr/bin/ sh

echo "underlier price      -> 145"
echo "strike price         -> 146.75"
echo "risk free rate       -> 0.005"
echo "time to maturity     -> 0.0833"
echo "underlier volatility -> 0.15"
echo "discount rate ->     -> 0.01"
echo ""

./pricing.x 145 146.75 0.005 0.0833 0.15 0.01
