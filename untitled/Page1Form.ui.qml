import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias verse: textArea1.text
    property alias flickable: flick
    property alias textArea: textArea1
    property alias close: close
    property alias closeTimer: timer

    Pane {
        id: leftPane
        width: frame1.width
        height: frame1.height
        z: 100
        padding: 0

        Flickable {
            anchors.fill: parent
            id: flick
            TextArea.flickable: textArea1
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {
            }
            TextArea {
                z: 100
                id: textArea1
                padding: 12
                textFormat: Text.AutoText
                wrapMode: Text.Wrap
                font.pixelSize: 18
                text: "This \n is\n some\n text"
                anchors.fill: parent
                readOnly: true
            }
        }
    }

    Pane {
        id: frame1
        y: parent.height * .5
        height: parent.height - parent.height * .5
        width: parent.width
        padding: 0

        ListView {
            id: listView1
            snapMode: ListView.SnapOneItem
            orientation: ListView.Horizontal
            anchors.fill: parent
            contentHeight: parent.height
            contentWidth: parent.width
            flickableDirection: Flickable.AutoFlickDirection

            delegate: Image {
                z: 80
                id: image1
                width: frame1.width
                height: frame1.height
                source: image
                fillMode: Image.PreserveAspectCrop
            }

            model: ListModel {
                ListElement {
                    image: "images/1Jn-4-1.jpg"
                }
                ListElement {
                    image: "images/1Jn-4-7.jpg"
                }
                ListElement {
                    image: "images/Acts-2-1.jpg"
                }
                ListElement {
                    image: "images/Ex-14-10.jpg"
                }
                ListElement {
                    image: "images/Gen-1-1.jpg"
                }
                ListElement {
                    image: "images/Gen-6-9.jpg"
                }
                ListElement {
                    image: "images/John-10-1.jpg"
                }
                ListElement {
                    image: "images/John-14-1.jpg"
                }
                ListElement {
                    image: "images/John-14-15.jpg"
                }
                ListElement {
                    image: "images/John-15-1.jpg"
                }
                ListElement {
                    image: "images/John-3-16.jpg"
                }
                ListElement {
                    image: "images/John-6-35.jpg"
                }
                ListElement {
                    image: "images/Luk-2-8.jpg"
                }
                ListElement {
                    image: "images/Mat-10-26.jpg"
                }
                ListElement {
                    image: "images/Mat-14-14.jpg"
                }
                ListElement {
                    image: "images/Mat-14-22.jpg"
                }
                ListElement {
                    image: "images/Mat-17-1.jpg"
                }
                ListElement {
                    image: "images/Mat-19-13.jpg"
                }
                ListElement {
                    image: "images/Mat-19-16.jpg"
                }
                ListElement {
                    image: "images/Mat-3-13.jpg"
                }
                ListElement {
                    image: "images/Mat-6-19.jpg"
                }
                ListElement {
                    image: "images/Mat-6-25.jpg"
                }
                ListElement {
                    image: "images/Mat-6-5.jpg"
                }
                ListElement {
                    image: "images/Mk-11-20.jpg"
                }
                ListElement {
                    image: "images/Mk-4-35.jpg"
                }
                ListElement {
                    image: "images/Ps-107-1.jpg"
                }
                ListElement {
                    image: "images/Rom-8-31.jpg"
                }
            }
        }
    }

    Button {
        id: close
        width: 35
        height: 35

        visible: false
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8

        text: qsTr("X")
        z: 100
        font.pixelSize: (height * .5)
    }

    Text {
        id: timer
        anchors.fill: close
        text: '5'
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        z: 100
        font.pixelSize: (height * .5)
    }

    Button {
        id: learnMore
        height: 49
        z: 110
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
            width: parent.width * .5
            height: parent.height
        }

        PropertyChanges {
            target: leftPane
            width: frame1.x
            height: parent.height
        }
    }
}
