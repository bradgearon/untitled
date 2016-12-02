import QtQuick 2.7

Page1Form {
    id: page1
    property var model
    property string imageName

    property int timerTotal: 5
    property int timerCurrent: 0

    Timer {
        id: timer
        running: false
        repeat: true
        onTriggered: function() {
            if(timerCurrent++ < timerTotal) {
                closeTimer.text = timerTotal - timerCurrent + '';
                return;
            }

            running = false;
            close.visible = true;
            closeTimer.visible = false;
        }
    }

    onModelChanged: function() {
        if(!model) {
            return;
        }

        timer.start();
        verse = model.verse;
    }

    close.onClicked: function() {
        main.close();
    }

    onWidthChanged: function() {
        if(width > height) {
            close.opacity = .75;
            closeTimer.opacity = .75;
        }
    }

    flickable.onContentYChanged: function() {
        if(!model || width > height) {
            close.opacity = .75;
            closeTimer.opacity = .75;
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
            closeTimer.opacity = .25;
            close.opacity = .25;
        } else {
            closeTimer.opacity = .75;
            close.opacity = .75;
        }

    }
}
