import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1000
    height: 900
    title: "Random Number Generator"

    Canvas {
        id: chartCanvas
        anchors.fill: parent
        anchors.margins: 20

        property var data: []

        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            var minY = randomNumberGenerator.min
            var maxY = randomNumberGenerator.max
            var rangeY = maxY - minY

            ctx.strokeStyle = "black"
            ctx.beginPath()
            ctx.moveTo(20, 0)
            ctx.lineTo(20, height)
            var zeroY = height - 20 - (0 - minY) * (height - 40) / rangeY
            ctx.moveTo(0, zeroY)
            ctx.lineTo(width, zeroY)
            ctx.stroke()

            ctx.strokeStyle = "blue"
            ctx.beginPath()
            for (var i = 0; i < data.length; i++) {
                var x = 20 + i * (width - 40) / data.length
                var y = height - 20 - (data[i] - minY) * (height - 40) / rangeY
                if (i === 0)
                    ctx.moveTo(x, y)
                else
                    ctx.lineTo(x, y)
                ctx.fillText(data[i].toString(), x, y - 5)
            }
            ctx.stroke()
        }

        Timer {
            interval: randomNumberGenerator.interval
            running: true
            repeat: true
            onTriggered: {
                if (chartCanvas.data.length > 100) {
                    chartCanvas.data.shift()
                }
                chartCanvas.data.push(randomNumberGenerator.number)
                chartCanvas.requestPaint()
            }
        }
    }

    Button {
        text: "Set Parameters"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        onClicked: settingsDialog.open()
    }

    Dialog {
        id: settingsDialog
        modal: true
        visible: false

        Column {
            spacing: 10
            padding: 20

            TextField {
                id: minField
                placeholderText: "Min"
                inputMethodHints: Qt.ImhDigitsOnly
                text: randomNumberGenerator.min.toString()
            }

            TextField {
                id: maxField
                placeholderText: "Max"
                inputMethodHints: Qt.ImhDigitsOnly
                text: randomNumberGenerator.max.toString()
            }

            TextField {
                id: intervalField
                placeholderText: "Interval (ms)"
                inputMethodHints: Qt.ImhDigitsOnly
                text: randomNumberGenerator.interval.toString()
            }

            Button {
                text: "Apply"
                onClicked: {
                    randomNumberGenerator.setMin(parseInt(minField.text))
                    randomNumberGenerator.setMax(parseInt(maxField.text))
                    randomNumberGenerator.start(parseInt(intervalField.text))
                    settingsDialog.close()
                }
            }
        }
    }
}
