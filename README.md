### general

* if app_webview exists 
    * need to grab value of cookies table name = read from app_webview/Cookies (sqlite)

```js
 JSON.parse( decodeURIComponent( decodeURI(a) ) );
```

```json
{
  "Luk-2-8": {
    "value": 0.5,
    "weight": 5
  }
}
```

selecting an element
========================


* exclude read for duration?
* read is value, either .5 for 

score weight changes when read value changes for one

save file
=========================

check for read value for element
if existing read value > 0, read till you find it
replace it and commit

    .^^_/*
      ( )

todo
-------------

* loop through and save read values to savefile
* load cultures
* load default / culture config
   * learn more text
* load picked element
  * handle index for he
* fix button color & ?close button
* rtl support
* learn more click + url parsing / handle
* add heading
* analytics

session / context object: 
 picker
 savefile
 active element
 signals when element changes
 cultureinfo
 book record for url
 config
 hides and shows ui


* narrow horizonal view with short text
* shrink vertical view with short text


text view thingee
* hold a QDataStream
* thread safe
* append to it
* on next draw, draw the new text

* accent color per image https://github.com/lokesh/color-thief/blob/master/src/color-thief.js

pinch zoom keeps text at center of pinch looking the same while other text blurs and the parent box expands until filling the screen, then it returns to normal state


