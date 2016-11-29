import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    title: qsTr("Hello World")
    visibility: "FullScreen"
    id: main
    property var model

    Page1 {
        anchors.fill: parent
        model: main.model
    }
}
