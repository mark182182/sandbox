defmodule Todo do
  @moduledoc """
  Documentation for Todo.
  """

  @doc """
  A basic todo application capable of adding, removing, updating and completing tasks.

  Functions:
  read_todo_list_from_file/1
  add_to_todo_list/1
  remove_from_todo_list/1
  complete_selected_task/1
  update_selected_task/2
  """
  def main do
    filename = String.trim(IO.gets("Please specifiy the file name!\n"))
    create_file_if_not_exists(filename)
    read_todo_list_from_file(filename)
  end

  def create_file_if_not_exists(filename) do
    if File.exists?(filename) == false do
      File.open(filename, [:write])
    end
  end

  def read_todo_list_from_file(filename) do
    String.split(File.read!(filename))
  end
end
