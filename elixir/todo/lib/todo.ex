defmodule Todo do
  def main do
    main_menu("0")
  end

  defp main_menu(cycle_break) when cycle_break === "5" do
    IO.puts("Bye.")
  end

  defp main_menu(cycle_break) do
    filename = "todo"

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
        main_menu(choice)

      choice === "2" ->
        IO.puts("Added: " <> add_to_todo_list(filename))
        main_menu(choice)

      choice === "3" ->
        IO.puts("Removed: " <> remove_from_todo_list(filename))
        main_menu(choice)

      choice === "4" ->
        IO.puts("Completed: " <> complete_selected_task(filename))
        main_menu(choice)

      choice === "5" ->
        main_menu(choice)
    end
  end

  def read_todo_list_from_file(filename) do
    File.stream!(filename)
    |> Enum.map(fn line -> line end)
    |> Enum.to_list()
  end

  def write_todo_list_to_file(filename, todo_list) do
    File.write!(filename, todo_list)
  end

  def add_to_todo_list(filename) do
    task = String.trim(IO.gets("Please write a new task:\n"))
    todo_list = read_todo_list_from_file(filename)

    if length(todo_list) < 1 do
      insert_first_task(filename, todo_list, task)
    else
      insert_task(filename, todo_list, task)
    end

    task
  end

  def insert_first_task(filename, todo_list, task) do
    todo_list = [todo_list | task <> "[]"]
    write_todo_list_to_file(filename, todo_list)
  end

  def insert_task(filename, todo_list, task) do
    todo_list = [todo_list | "\n" <> task <> "[]"]
    write_todo_list_to_file(filename, todo_list)
  end

  def remove_from_todo_list(filename) do
    task = String.trim(IO.gets("Which task would you like to delete?\n"))
    todo_list = read_todo_list_from_file(filename)

    todo_list =
      Enum.filter(todo_list, fn x ->
        uncompleted_task = task <> "[]" <> "\n"
        completed_task = task <> "[\u{2713}]" <> "\n"
        x != uncompleted_task || x != completed_task
      end)

    IO.puts(todo_list)
    write_todo_list_to_file(filename, todo_list)
    task
  end

  def complete_selected_task(filename) do
    task = String.trim(IO.gets("Which task would you like to complete?\n"))
    todo_list = read_todo_list_from_file(filename)
    todo_list = String.replace(List.to_string(todo_list), task <> "[]", task <> "[\u{2713}]")
    write_todo_list_to_file(filename, todo_list)
    task
  end
end
