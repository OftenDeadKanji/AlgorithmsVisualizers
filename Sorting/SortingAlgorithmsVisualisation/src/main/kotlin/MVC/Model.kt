package MVC

import MVC.Sorter.*
import MVC.command.Command
import kotlin.random.Random

class Model
{
    var command = Command.None
    var array = arrayOf<Int>()
    var index = 0
    private var sorter: Sorter = IdleSorter()

    var milisecToWait : Long = 10

    var endCommand = false
    var endAnswer = false

    fun update()
    {
        if (!endCommand)
        {
            when (command)
            {
                Command.Sort ->
                {
                    Thread.sleep(milisecToWait)
                    oneSortingIteration()
                }
            }
        }
        else if (!endAnswer)
        {
            endAnswer = true
        }
    }

    private fun oneSortingIteration()
    {
        index = sorter.sortAndReturnIndex(array, index)
        if (isSorted())
        {
            command = Command.None
            index = -2
        }
    }

    private fun isSorted(): Boolean
    {
        for (i in 0 until array.size - 1)
            if (array[i] > array[i + 1])
                return false

        return true
    }

    fun changeSorter(algorithmType: SortingAlgorithmType)
    {
        sorter = when (algorithmType)
        {
            SortingAlgorithmType.BUBBLE -> BubbleSorter()
            SortingAlgorithmType.INSERTION -> InsertionSorter()
            SortingAlgorithmType.BOGO -> BogoSorter()
            SortingAlgorithmType.QUICK -> QuickSorter()
            else -> IdleSorter()
        }
    }

    fun startSorting(arraySize: Int)
    {
        array = Array(arraySize) { Random.nextInt(1, arraySize + 1) }
        index = 0
    }

}