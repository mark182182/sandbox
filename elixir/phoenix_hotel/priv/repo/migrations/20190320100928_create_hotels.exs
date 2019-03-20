defmodule PhoenixHotel.Repo.Migrations.CreateHotels do
  use Ecto.Migration

  def change do
    create table(:hotels) do
      add :name, :string
      add :location, :string
      add :capacity, :integer

      timestamps()
    end

  end
end
