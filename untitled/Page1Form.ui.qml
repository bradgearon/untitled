import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

Item {
    anchors.fill: parent
    id: item1
    property alias mainImage: image1.source
    property alias verse: textArea1.text
    property alias flickable: flick
    property alias textArea: textArea1
    property alias close: close
    property alias learnMore: learnMore
    property alias closeTimer: timer
    property alias learnMoreX: learnMore.x
    property alias closeX: close.x

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
            ScrollBar.vertical: ScrollBar {
                width: 4
                background.visible: false
            }

            TextArea {
                id: textArea1

                anchors.fill: parent

                rightPadding: 15
                leftPadding: 14
                topPadding: 14
                bottomPadding: 14
                horizontalAlignment: isRtl ? Text.AlignRight : Text.AlignLeft
                textFormat: Text.AutoText
                wrapMode: Text.Wrap
                font.pixelSize: 22

                text: "<big><b>This is some text</b></big><br />Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer vel massa a tortor suscipit tincidunt nec malesuada nunc. Aenean porta tortor et eros tempor, venenatis blandit magna egestas. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Fusce tincidunt massa dui, in condimentum elit blandit ac. Nulla tempor vel nunc at pellentesque. Aenean luctus justo quam, nec ultricies nulla auctor et. Proin eleifend velit sed interdum rutrum. Maecenas sed bibendum nisl, non vestibulum ligula. Integer in vulputate odio. In vitae feugiat ex. Duis nec ligula at tortor vulputate facilisis. Sed aliquam lorem at nibh suscipit rutrum. Aliquam quis ex est. Donec et feugiat odio, eu semper nulla. Sed auctor et lacus in imperdiet. Aliquam et ornare ante. Maecenas suscipit fringilla orci. Praesent elementum mi mauris, eu pretium mauris efficitur vitae. Nulla suscipit ligula in eros congue fermentum. Aliquam ultrices, mi quis sagittis gravida, libero odio ultricies arcu, quis pretium dolor est nec ligula. Nunc porttitor ligula non nisl volutpat ultrices. Etiam eget leo et mi volutpat bibendum quis at est."
                font.family: "Roboto"

                readOnly: true
                background: null
            }
        }
    }

    Flickable {
        id: frame1
        y: parent.height * .5
        height: parent.height - parent.height * .5
        z: 5
        width: parent.width
        contentWidth: image1.width
        contentHeight: image1.height
        boundsBehavior: Flickable.StopAtBounds

        Image {
            id: image1
            width: frame1.width
            height: frame1.height
            source: "images/Ex-14-10.jpg"
            fillMode: Image.PreserveAspectCrop
        }
    }

    Button {
        id: close
        x: 590
        width: height - 10
        visible: false
        text: qsTr("X")
        Material.elevation: 1

        anchors.topMargin: 8
        anchors.leftMargin: 12
        anchors.top: parent.top

        opacity: .75
        z: 10
        font.pixelSize: (height * .35)
    }

    Text {
        id: timer
        color: "#6d6d6d"
        text: '5'
        anchors.fill: close
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        z: 10
        font.pixelSize: (height * .5)
    }

    Button {
        id: learnMore
        x: 505
        z: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 7
        text: qsTr("Learn More...")
        highlighted: true
        bottomPadding: 20
        topPadding: 20
        padding: 16
    }

    states: [

        State {
            name: "horizontalFlipped"
            when: page1.width > page1.height && isRtl

            PropertyChanges {
                target: frame1

                y: 0
                width: parent.width * .5
                height: parent.height
            }

            PropertyChanges {
                target: leftPane
                x: parent.width * .5
                width: frame1.width
                height: parent.height
            }
        },

        State {
            name: "horizontal"
            when: page1.width > page1.height && !isRtl

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
    ]
}
