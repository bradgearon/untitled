import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias verse: textArea1.text
    property alias flickable: flick
    property alias textArea: textArea1
    property alias close: close

    Flickable {
        anchors.bottom: frame1.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        id: flick
        TextArea.flickable: textArea1
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar {
        }

        TextArea {
            id: textArea1
            width: parent.width
            height: parent.height
            padding: 14
            textFormat: Text.AutoText
            wrapMode: Text.Wrap
            font.pixelSize: 18
            readOnly: true
        }
    }

    Button {
        id: close
        width: 35
        height: 35

        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8

        text: qsTr("X")
        font.pixelSize: (height * .5)
    }

    Pane {
        id: frame1
        y: parent.height * .5
        height: parent.height - parent.height * .5
        width: parent.width
        padding: 3.5

        Image {
            id: image1
            anchors.fill: parent
            source: "1Jn-4-1.jpg"
            fillMode: Image.PreserveAspectFit
        }
    }

    Button {
        id: learnMore
        height: 49

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 7
        anchors.right: parent.right
        anchors.rightMargin: 7
        padding: 14
        font.pixelSize: (height * .5) - 7

        text: qsTr("Learn More...")
        rightPadding: 21
        leftPadding: 21
        topPadding: 14
    }
}
