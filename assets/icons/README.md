# Icons For Template Stack

## Description

There are icons for **Template Stack** (e.g. logo)

## Requirements

+ **Inkscape** - editor for making & exporting icons
+ **Meson + Ninja** - build system
+ **SVGo** (optional) - SVG optimizer to remove trash

## Adding/Editing Icons

To add/edit an icon, use **Inkscape**

Place the files in the ./source directory

## Building

Building does several things:

+ converts _Inkscape SVG_ to a _Plain SVG_ (raw files)
+ optimizes these icons, if **SVGo** is installed (optimized files)
+ exports PNG files in provided scaling resolutions

To build icons, run these commands:

```bash
$ meson setup build
$ cd build
$ meson compile
```

After building, these files will be created:

+ `file-R.svg` (raw files)
+ `file-O.svg` (optimized files)
+ `file@1.png` (png export at specified scaling resolutions that is a number after `@`)

> [!NOTE]
> **Meson** creates a `.gitignore` file in build directory, so to add these files to repository, use:
> ```bash
> $ git add -f *.png *.svg
> ```
