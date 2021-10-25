# Mixed utility codes

## Like all displayed songs in a playlist (Spotify Browser)
``` js
const rows = document.querySelectorAll("div[role=row]");
for (const i in rows) {
  const row = rows[i];
  const currRow = row.querySelectorAll("div")[8];
  if (currRow.innerHTML.includes("button")) {
    const button = currRow.querySelector("button");
    if (button.outerHTML.includes("Save to Your Library"))
      {
        button.click();
      }
  }
}
```
