reader = open('./text.txt')
try:
  print('Something')
  text = list(reader)
  print(text)
  num = 0
  for i in text:
      num+=1
      print(i)
  print(num)

  writer = open('./output.txt', 'w')
  try: 
    writer.write(''.join(text))
  finally:
    writer.close()
finally:
  reader.close()
