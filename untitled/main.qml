import QtQuick 2.7
import QtQuick.Controls 2.1

Rectangle {
    id: main
    anchors.fill: parent
    color: "#00FFFFFF"
    visible: true
    property var model

    Page1 {
        anchors.fill: parent
        model: main.model
    }
}
