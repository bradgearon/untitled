import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

ApplicationWindow {
    id: item1

    TextArea {
        id: text1
        text: qsTr("testest este teset")
        textFormat: Text.AutoText
        anchors.bottom: image1.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        font.family: "Verdana"
        wrapMode: Text.WordWrap
        font.pixelSize: 144
        readOnly: true

    }

    Rectangle {
        id: image1
        y: parent.height * .5
        width: parent.width
        height: parent.height - parent.height * .5
        color: "#4a2222"
        // fillMode: Image.PreserveAspectFit
    }
}
