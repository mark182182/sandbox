# Mixed utility codes

## Like all displayed songs in a playlist (Spotify Browser)
``` js
const rows = document.querySelectorAll("div[role=row]");
for (const i in rows) {
  const row = rows[i];
  if (row instanceof Node && row.outerHTML.includes("tracklist-row")) {
    const innerRows = row.querySelector("div").querySelectorAll("div");
    const currRow = innerRows[innerRows.length - 2];
    if (currRow.innerHTML.includes("button")) {
      const button = currRow.querySelector("button");
      if (button.outerHTML.includes("add-button") && button.outerHTML.includes('aria-checked="false"')) {
        button.click();
      }
    }
  }
}
```

## Windows stuff:
- Windows+Ctrl+Arrow -> Move between virtual desktops
- Windows+Ctrl+D -> Create a new virtual desktop
