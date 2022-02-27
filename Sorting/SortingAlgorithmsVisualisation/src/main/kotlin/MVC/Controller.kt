package MVC

import MVC.Sorter.SortingAlgorithmType
import MVC.command.Command

class Controller {
    private var model = Model()
    private var view = View(this)

    enum class EventType {

    }

    private val viewEventQueue = ArrayDeque<EventType>()

    fun updateModelAndView() {
        model.update()
        view.drawArray(model.array, model.index)
    }

    fun sortButtonCallback(arraySize : Int, algorithmType : SortingAlgorithmType)
    {
        model.endCommand = true
        while(!model.endAnswer)

        model.changeSorter(algorithmType)
        model.startSorting(arraySize)
        model.command = Command.Sort

        model.endCommand = false
        model.endAnswer = false
    }

    fun changeSpeedSliderCallback(minValue : Long, maxValue : Long, speed : Long)
    {
        val a = (maxValue - minValue) / (minValue - maxValue)
        val b = maxValue - a * minValue
        model.milisecToWait = a * speed + b
    }
}