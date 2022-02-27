package MVC

import MVC.Sorter.SortingAlgorithmType
import java.awt.Color
import java.awt.Dimension
import java.awt.Rectangle
import javax.swing.*

import javax.swing.JButton
import java.awt.Graphics2D

import java.awt.Graphics
import java.awt.geom.Rectangle2D

class View(private val controller: Controller)
{
    private var frame: JFrame = JFrame("Sorting algorithm visualisation")
    private var sortPanel = SortPanel()

    private val borderPosX = 1300
    private val windowSize = Dimension(1600, 900)

    init
    {
        frame.layout = null
        frame.size = windowSize

        createPanels()

        frame.defaultCloseOperation = JFrame.EXIT_ON_CLOSE
        frame.isVisible = true
    }

    fun drawArray(array: Array<Int>, index: Int)
    {
        sortPanel.array = array
        sortPanel.index = index

        frame.validate()
        frame.repaint()
    }

    private fun createPanels()
    {
        frame.add(createSortPanel())
        frame.add(createUIPanel())
    }

    private fun createSortPanel(): JPanel
    {
        sortPanel.bounds = Rectangle(0, 0, borderPosX, windowSize.height)
        sortPanel.background = Color.LIGHT_GRAY

        return sortPanel
    }

    private fun createUIPanel(): JPanel
    {
        val UIPanel = JPanel()
        UIPanel.layout = null
        UIPanel.bounds = Rectangle(borderPosX, 0, windowSize.width - borderPosX, windowSize.height)
        UIPanel.background = Color.WHITE

        val spinner = createArraySizeSpinner(UIPanel)
        val comBox = createAlgorithmsComboBoxWithLabel(UIPanel)
        createStartButton(UIPanel, spinner, comBox)
        createSpeedSliderWithLabel(UIPanel)

        return UIPanel
    }

    private fun createArraySizeSpinner(parent: JPanel): JSpinner
    {
        val label = JLabel("Array size:")

        var xPos = ((parent.preferredSize.width - label.preferredSize.width) * 0.5).toInt()
        label.bounds = Rectangle(xPos, 130, label.preferredSize.width, label.preferredSize.height)
        parent.add(label)

        val arraySizeSpinner = JSpinner(SpinnerNumberModel(100, 2, 100000, 1))

        xPos = ((parent.preferredSize.width - arraySizeSpinner.preferredSize.width) * 0.5).toInt()
        arraySizeSpinner.bounds = Rectangle(xPos, 150, arraySizeSpinner.preferredSize.width, arraySizeSpinner.preferredSize.height)

        parent.add(arraySizeSpinner)

        return arraySizeSpinner
    }

    private fun createAlgorithmsComboBoxWithLabel(parent: JPanel): JComboBox<String>
    {
        val label = JLabel("Sorting algorithm:")

        var xPos = ((parent.preferredSize.width - label.preferredSize.width) * 0.5).toInt()
        label.bounds = Rectangle(xPos, 70, label.preferredSize.width, label.preferredSize.height)
        parent.add(label)

        val sortingAlgorithms = arrayOf("Bubble", "Insertion", "Bogo", "Quick")
        val comboBox = JComboBox(sortingAlgorithms)

        xPos = ((parent.preferredSize.width - comboBox.preferredSize.width) * 0.5).toInt()
        comboBox.bounds = Rectangle(xPos, 90, comboBox.preferredSize.width, comboBox.preferredSize.height)

        parent.add(comboBox)

        return comboBox
    }

    private fun createStartButton(parent: JPanel, arraySizeSpinner: JSpinner, algorithmComboBox: JComboBox<String>): JButton
    {
        val sortButton = JButton("Sort")

        val xPos = ((parent.preferredSize.width - sortButton.preferredSize.width) * 0.5).toInt()
        sortButton.bounds = Rectangle(xPos, 300, sortButton.preferredSize.width, sortButton.preferredSize.height)

        sortButton.addActionListener {
            controller.sortButtonCallback(arraySizeSpinner.value as Int, SortingAlgorithmType.StringToEnum(algorithmComboBox.selectedItem as String))
        }

        parent.add(sortButton)

        return sortButton
    }

    private fun createSpeedSliderWithLabel(parent: JPanel): JSlider
    {
        val label = JLabel("Speed:")

        var xPos = ((parent.preferredSize.width - label.preferredSize.width) * 0.5).toInt()
        label.bounds = Rectangle(xPos, 190, label.preferredSize.width, label.preferredSize.height)
        parent.add(label)

        val minSpeed = 1
        val maxSpeed = 100
        val initSpeed = 50

        val speedSlider = JSlider(JSlider.HORIZONTAL, minSpeed, maxSpeed, initSpeed)

        xPos = ((parent.preferredSize.width - speedSlider.preferredSize.width) * 0.5).toInt()
        speedSlider.bounds = Rectangle(xPos, 210, speedSlider.preferredSize.width, speedSlider.preferredSize.height)

        speedSlider.addChangeListener {
            controller.changeSpeedSliderCallback(minSpeed.toLong(), maxSpeed.toLong(), speedSlider.value.toLong())
        }

        parent.add(speedSlider)

        return speedSlider
    }

    private class SortPanel : JPanel()
    {
        var array = arrayOf<Int>()
        var index = 0

        override fun paintComponent(g: Graphics)
        {
            super.paintComponent(g)

            val widthOffset = 50.0f
            val heightOffset = 100.0f

            val rectWidth = (this.width.toFloat() - 2 * widthOffset) / array.size.toFloat()
            val maxRectHeight = this.height - 2 * heightOffset

            var maxValueInArray = 0
            for (value in array)
            {
                if (value > maxValueInArray)
                    maxValueInArray = value
            }

            val g2d = g as Graphics2D
            for (i in array.indices)
            {
                g2d.color = when (index)
                {
                    i -> Color.RED
                    -2 -> Color.GREEN
                    else -> Color.YELLOW
                }

                val rectHeight = array[i].toFloat() / maxValueInArray * maxRectHeight
                val x = widthOffset + i * rectWidth
                val y = heightOffset + maxRectHeight - rectHeight

                val rect = Rectangle2D.Float(x, y, rectWidth, rectHeight)

                g2d.fill(rect)
                g2d.color = Color.BLACK
                g2d.draw(rect)

            }
        }
    }
}