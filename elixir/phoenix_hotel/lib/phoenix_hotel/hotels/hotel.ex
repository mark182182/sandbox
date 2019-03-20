defmodule PhoenixHotel.Hotels.Hotel do
  use Ecto.Schema
  import Ecto.Changeset

  schema "hotels" do
    field :capacity, :integer
    field :location, :string
    field :name, :string

    timestamps()
  end

  @doc false
  def changeset(hotel, attrs) do
    hotel
    |> cast(attrs, [:name, :location, :capacity])
    |> validate_required([:name, :location, :capacity])
  end
end
