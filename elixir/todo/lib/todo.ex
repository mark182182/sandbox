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
    main_menu()
  end

  def main_menu do
    filename = "todo"
    create_file_if_not_exists(filename)

    choice =
      String.trim(
        IO.gets(
          "What would you like to do?\n" <>
            "1 - List all tasks\n" <>
            "2 - Add a task\n" <>
            "3 - Remove a task\n" <>
            "4 - Complete a task\n" <>
            "5 - Exit\n"
        )
      )

    cond do
      choice === "1" ->
        IO.puts(read_todo_list_from_file(filename))

      choice === "2" ->
        add_to_todo_list(filename)

      choice === "3" ->
        remove_from_todo_list(filename)

      choice === "4" ->
        nil

      choice === "5" ->
        nil
    end
  end

  def create_file_if_not_exists(filename) do
    if File.exists?(filename) == false do
      File.open(filename, [:write])
    end
  end

  def read_todo_list_from_file(filename) do
    File.stream!(filename)
    |> Enum.map(fn line -> line end)
    |> Enum.to_list()
  end

  def write_todo_list_to_file(filename, todo_list, task) do
    File.write!(filename, todo_list)
    IO.puts("Added " <> task)
  end

  def add_to_todo_list(filename) do
    task = String.trim(IO.gets("Please write a new task:\n"))
    todo_list = read_todo_list_from_file(filename)

    if length(todo_list) < 1 do
      insert_first_task(filename, todo_list, task)
    else
      insert_task(filename, todo_list, task)
    end
  end

  def insert_first_task(filename, todo_list, task) do
    todo_list = [todo_list | task <> "[]"]
    write_todo_list_to_file(filename, todo_list, task)
  end

  def insert_task(filename, todo_list, task) do
    todo_list = [todo_list | "\n" <> task <> "[]"]
    write_todo_list_to_file(filename, todo_list, task)
  end

  def remove_from_todo_list(filename) do
    task = String.trim(IO.gets("Which task would you like to delete?\n"))
    todo_list = read_todo_list_from_file(filename)
    todo_list = Enum.filter(todo_list, fn x -> x != task <> "[]" end)
    File.write!(filename, todo_list)
    IO.puts("Removed: " <> task)
  end
end
