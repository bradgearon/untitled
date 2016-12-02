import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    id: main
    visible: true
    property var model
    property string imageName

    Page1 {
        anchors.fill: parent
        model: main.model
    }
}
