import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1

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
        z: 10
        padding: 0
        Material.elevation: 4

        Flickable {
            anchors.fill: parent
            id: flick
            TextArea.flickable: textArea1
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar { }

            TextArea {
                id: textArea1

                anchors.fill: parent
                rightPadding: 14
                leftPadding: 14
                topPadding: 14
                bottomPadding: 0

                textFormat: Text.AutoText
                wrapMode: Text.Wrap

                font.pixelSize: 18
                text: "<big><b>This is some text</b></big><br />Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer vel massa a tortor suscipit tincidunt nec malesuada nunc. Aenean porta tortor et eros tempor, venenatis blandit magna egestas. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Fusce tincidunt massa dui, in condimentum elit blandit ac. Nulla tempor vel nunc at pellentesque. Aenean luctus justo quam, nec ultricies nulla auctor et. Proin eleifend velit sed interdum rutrum. Maecenas sed bibendum nisl, non vestibulum ligula. Integer in vulputate odio. In vitae feugiat ex. Duis nec ligula at tortor vulputate facilisis. Sed aliquam lorem at nibh suscipit rutrum. Aliquam quis ex est. Donec et feugiat odio, eu semper nulla. Sed auctor et lacus in imperdiet. Aliquam et ornare ante. Maecenas suscipit fringilla orci. Praesent elementum mi mauris, eu pretium mauris efficitur vitae. Nulla suscipit ligula in eros congue fermentum. Aliquam ultrices, mi quis sagittis gravida, libero odio ultricies arcu, quis pretium dolor est nec ligula. Nunc porttitor ligula non nisl volutpat ultrices. Etiam eget leo et mi volutpat bibendum quis at est."

                font.family: "Roboto"
                readOnly: true

            }
        }

    }

    Pane {
        id: frame1
        y: parent.height * .5
        height: parent.height - parent.height * .5
        z: 5
        width: parent.width
        padding: 0

        ListView {
            id: listView1
            z: 10
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
        width: height - 10
        visible: true
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 12

        text: qsTr("X")
        Material.elevation: 1
        opacity: .75
        z: 10
        font.pixelSize: (height * .35)
    }

    Text {
        id: timer
        anchors.fill: close
        text: '5'
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        z: 10
        font.pixelSize: (height * .5)
    }

    Button {
        id: learnMore
        z: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 7
        anchors.right: parent.right
        anchors.rightMargin: 7

        // onLinkActivated: Qt.openUrlExternally(link)

        text: qsTr("Learn More...")
        highlighted: true
        bottomPadding: 20
        topPadding: 20
        padding: 16
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


    }
}
