defmodule PhoenixHotel.Repo do
  use Ecto.Repo,
    otp_app: :phoenix_hotel,
    adapter: Ecto.Adapters.Postgres
end
