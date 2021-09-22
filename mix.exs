defmodule Pricing.Mixfile do
  use Mix.Project

  def project do
    [app: :pricing,
     description: "Pricing financial instruments in Elixir",
     version: "0.0.1",
     elixir: "~> 1.2",
     build_embedded: Mix.env == :prod,
     start_permanent: Mix.env == :prod,
     deps: deps,
     package: package]
  end

  # Configuration for the OTP application
  #
  # Type "mix help compile.app" for more information
  def application do
    [
      applications: [:logger, :tzdata, :porcelain]
    ]
  end


  defp package do
    [ files: ["lib", "priv", "mix.exs", "README.md", "LICENSE.md"],
      maintainers: ["Arthur Colle"],
      licenses: ["Colle"],
      links: %{ "GitHub": "https://github.com/arthurcolle/pricing" } ]
  end

  defp deps do
    [
      {:plug, "~> 1.3"},
      {:timex, "~> 1.0.0"},
      {:porcelain, "~> 2.0.1"},
      {:poison, "~> 3.1.0"}
    ]
  end
end
