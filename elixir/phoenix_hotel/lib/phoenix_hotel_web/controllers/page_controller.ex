defmodule PhoenixHotelWeb.PageController do
  use PhoenixHotelWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end
end
