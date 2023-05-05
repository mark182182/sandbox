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

## Create animated gif from a set of jpeg images
``` shell
First convert the images to a video:

ffmpeg -f image2 -i image%d.jpg video.avi
(This will convert the images from the current directory (named image1.jpg, image2.jpg...) to a video file named video.avi.)

Then convert the avi to a gif:

ffmpeg -i video.avi -pix_fmt rgb24 -loop_output 0 out.gi
```

## Windows stuff:
- Windows+Ctrl+Arrow -> Move between virtual desktops
- Windows+Ctrl+D -> Create a new virtual desktop
