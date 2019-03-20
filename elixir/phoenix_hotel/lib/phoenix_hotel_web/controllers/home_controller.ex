defmodule PhoenixHotelWeb.HomeController do
  use PhoenixHotelWeb, :controller

  def home(conn, _params) do
    render(conn, "home.html")
  end

  def hotel(conn, %{"hotel" => hotel}) do
    render(conn, "hotel.html", hotel: hotel)
  end
end
