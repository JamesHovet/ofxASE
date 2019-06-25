ofxASE: An Adobe .ase Swatch Importer for Open Frameworks
==========================

![alt text](./example_Great_Wave.png "AdobeColor Under the Wave off Kanagawa - Katsushika Hokusai.ase")

About
-------
ofxASE lets you import color swatches like those from [Adobe Color](https://color.adobe.com/) or other Adobe products into your openFrameworks project. This lets you quickly set and dynamically change the color palette of a project.

Usage
-------

```cpp
ofxASE swatch;
swatch.load("swatches/AdobeColor Under the Wave off Kanagawa - Katsushika Hokusai.ase");

for(auto namedColor : swatch.getAllColors()){
    ofLog() << namedColor.color;
}
```

Installation
------------
clone ofxASE into the addons folder of your openFrameworks installation. A basic example and an example specifically on color groups are included with the addon.

Brief Documentation
-----------------------

### Loading Swatches:
A swatch can be loaded in with multiple .ase files. Each file's contents are added to the swatch instance. Swatches can be cleared with `.clear()`
```cpp
ofxASE swatch;
swatch.load("swatches/example_1.ase");
swatch.load("swatches/example_2.ase");

swatch.clear();
```

### Getting Colors:
To get all the colors in a swatch, use the `.getAllColors()` method. This returns a `std::vector` of type `NamedColor`. `NamedColor`'s can be implicitly treated like `ofColor`'s but also have a `.name` field and an explicit `.color`

```cpp
for(ofxASE::NamedColor namedColor : swatch.getAllColors()){
    ofLog() << namedColor.name << " : " << namedColor.color;
}
```

### Working with Groups:
Use `.getGroups()` to get all the color groups within a swatch. This method returns a `std::vector` of type `NamedColorGroup`. Each `NamedColorGroup` has a `.name` field and a `.getColors()` method which returns a `std::vector` of type `NamedColor`.

```cpp
for(ofxASE::NamedColorGroup group : swatch.getGroups()){
    ofLog() << group.name;
    for(ofxASE::NamedColor namedColor : group.getColors()){
        ofLog() << "|" << namedColor.name;
    }
}
```

License
-------
MIT License - Copyright (c) 2019 James Hovet
