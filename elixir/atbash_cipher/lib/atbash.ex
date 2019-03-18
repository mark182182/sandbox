defmodule Atbash do
  def main do
    decode_to_atbash()
  end

  def decode_to_atbash do
    default_alphabet = "abcdefghijklmnopqrstuvwxyz"
    atbash_alphabet = "zyxwvutsrqponmlkjihgfedcba"

    Enum.each(String.to_charlist(get_input_from_user()), fn character -> IO.puts <<character>> end)
  end

  def get_input_from_user do
    user_input = IO.gets("Please input a sentence to decode!\n")
    String.trim(user_input)
  end
end
