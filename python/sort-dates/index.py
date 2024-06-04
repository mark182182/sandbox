import re

def main():
  p  = re.compile("[(]\d*")
  booksFile = open("books")
  books = booksFile.readlines()
  booksFile.close()
  bcs = {}
  ads = {}
  for i in books:
    index = int(p.search(i).group()[1:])
    if "BC" in i:
      bcs[index] = i
    else:
      ads[index] = i
  bcsorted = sorted(bcs.items(), key=lambda item: item[0], reverse=True)
  adsorted = sorted(ads.items(), key=lambda item: item[0])
  s = open("sorted", "w")
  for i in bcsorted:
    s.write(i[1])
  for i in adsorted:
    s.write(i[1])
  s.close()
  return 0


if __name__ == "__main__":
  main();
