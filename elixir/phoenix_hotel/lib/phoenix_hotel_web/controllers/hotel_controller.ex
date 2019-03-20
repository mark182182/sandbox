defmodule PhoenixHotelWeb.HotelController do
  use PhoenixHotelWeb, :controller

  alias PhoenixHotel.Hotels
  alias PhoenixHotel.Hotels.Hotel

  action_fallback PhoenixHotelWeb.FallbackController

  def index(conn, _params) do
    hotels = Hotels.list_hotels()
    render(conn, "index.json", hotels: hotels)
  end

  def create(conn, %{"hotel" => hotel_params}) do
    with {:ok, %Hotel{} = hotel} <- Hotels.create_hotel(hotel_params) do
      conn
      |> put_status(:created)
      |> put_resp_header("location", Routes.hotel_path(conn, :show, hotel))
      |> render("show.json", hotel: hotel)
    end
  end

  def show(conn, %{"id" => id}) do
    hotel = Hotels.get_hotel!(id)
    render(conn, "show.json", hotel: hotel)
  end

  def update(conn, %{"id" => id, "hotel" => hotel_params}) do
    hotel = Hotels.get_hotel!(id)

    with {:ok, %Hotel{} = hotel} <- Hotels.update_hotel(hotel, hotel_params) do
      render(conn, "show.json", hotel: hotel)
    end
  end

  def delete(conn, %{"id" => id}) do
    hotel = Hotels.get_hotel!(id)

    with {:ok, %Hotel{}} <- Hotels.delete_hotel(hotel) do
      send_resp(conn, :no_content, "")
    end
  end
end
