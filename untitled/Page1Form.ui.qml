import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias verse: textArea1.text
    property alias flickable: flick
    property alias textArea: textArea1
    property alias close: close

    Flickable {
        width: frame1.width
        height: frame1.height
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
            text: "This \n is\n some\n text"
            readOnly: true


        }
    }

    Pane {
        id: frame1
        y: parent.height * .5
        height: parent.height - parent.height * .5
        bottomPadding: 0
        rightPadding: 0
        leftPadding: 0
        topPadding: 0
        width: parent.width
        padding: 14

        Image {
            id: image1
            clip: true
            anchors.fill: parent
            source: "1Jn-4-1.jpg"
            fillMode: Image.PreserveAspectFit
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

    states: State {
        name: "horizontal"
        when: page1.width > page1.height

        PropertyChanges {
            target: frame1
            x: parent.width * .5
            y: 0
            width: parent.width / 2
            height: parent.height
        }

        PropertyChanges {
            target: flick
            width: parent.width / 2
            height: parent.height
        }

    }
}
