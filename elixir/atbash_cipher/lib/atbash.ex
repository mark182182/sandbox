defmodule Atbash do
  def main do
    List.to_string(decode_to_atbash())
  end

  def decode_to_atbash do
    default_alphabet = "abcdefghijklmnopqrstuvwxyz"
    atbash_alphabet = "zyxwvutsrqponmlkjihgfedcba"
    Enum.map(String.to_charlist(get_input_from_user()), fn character ->
      character_index = :binary.match default_alphabet, <<character>>
      character_index = Kernel.elem(character_index, 0)
      String.at(atbash_alphabet, character_index)
    end)
  end
  def get_input_from_user do
    user_input = IO.gets("Please input a word to decode!\n")
    String.downcase(String.trim(user_input))
  end
end
