import QtQuick 2.6

Page1Form {
    id: page1
    property var model
    property int timerTotal: 5
    property int timerCurrent: 0
    property bool isRtl: true
    anchors.fill: parent

    Timer {
        id: timer
        running: false
        repeat: true
        triggeredOnStart: false
        onTriggered: function() {
            if(timerCurrent === 0) {
                model.onShow();
            }

            if(timerCurrent++ < timerTotal) {
                console.log("triggered");
                closeTimer.text = timerTotal - timerCurrent + '';
                return;
            }

            close.visible = true;
            closeTimer.visible = false;
            running = false;
        }
    }

    onModelChanged: function() {
        console.log("model changed");
        verse = "";
        mainImage = "";

        if(!model) {
            return;
        }

        learnMoreText = model.more;
        verse = model.verse;
        isRtl = model.isRtl;
        mainImage = model.imageName;

        if(isRtl) {
            close.anchors.right = undefined;
            close.anchors.left = close.parent.left;

            learnMore.anchors.right = undefined;
            learnMore.anchors.left = learnMore.parent.left;
        } else {
            close.anchors.left = undefined;
            close.anchors.right = close.parent.right;

            learnMore.anchors.left = undefined;
            learnMore.anchors.right = learnMore.parent.right;
        }
    }

    image1.onStatusChanged: function(status) {
        if(!timer.running && image1.status === Image.Ready) {
            console.log(image1.source);
            model.onReady();
            console.log("starting timer");

            closeTimer.text = 5 + '';
            timerCurrent = 0;
            close.visible = false;
            closeTimer.visible = true;

            timer.start();
        }
    }

    close.onClicked: function() {
        if(!model) {
            return;
        }
        model.onClose();
        timer.restart();
    }

    learnMore.onClicked: function() {
        if(!model) {
            return;
        }

        model.onRead(1.0);
        model.onLearnMore();
    }

    onWidthChanged: function() {
        if(width > height) {
            close.opacity = .75;
            closeTimer.opacity = .75;
        }
    }

    flickable.onAtYEndChanged: function() {
        if(!model || flickable.height === 0
                || textArea.height < flickable.height) {
            return;
        }

        if(flickable.atYEnd) {
            model.onRead(.5);
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

