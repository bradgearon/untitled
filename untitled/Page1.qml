import QtQuick 2.7

Page1Form {
    id: page1
    property var model
    onModelChanged: function() {
        if(!model) {
            return;
        }

        verse = model.verse;
    }

    flickable.onContentYChanged: function() {
        if(!model) {
            return;
        }

        var spot = flickable.mapToItem(textArea, flickable.width - 35, 35);
        var position = textArea.positionAt(spot.x, spot.y);
        var leftPos = position - 1;
        if(leftPos < 0) {
            leftPos = 0;
        }
        var midRect = textArea.positionToRectangle(position);
        var leftRect = textArea.positionToRectangle(leftPos);
        var rect = textArea.positionToRectangle(position + 1);

        var touching = false;
        if(spot.x - close.width < rect.x
                || spot.x - close.width < midRect.x
                || spot.x - close.width < leftRect.x) {
            touching = true;
        }

        var isInButton = touching;
        if(isInButton) {
            close.opacity = .15;
        } else {
            close.opacity = 1;
        }

    }
}
