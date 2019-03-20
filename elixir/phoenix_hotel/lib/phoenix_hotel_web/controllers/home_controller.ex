defmodule PhoenixHotelWeb.HomeController do
  use PhoenixHotelWeb, :controller

  def home(conn, _params) do
    render(conn, "home.html")
  end
end
