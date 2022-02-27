package MVC.Sorter

class QuickSorter : Sorter()
{
    enum class Mode
    {
        INIT, CHOOSING_DIVIDE_INDEX, SWAPPING_DIVIDE_AND_RIGHT_VALUE, SORTING, AFTER_PARTIAL_SORTING
    }

    private var leftIndex = 0
    private var rightIndex = 1
    private var index = 0
    private var currentPosition = 0

    private var divideIndex = 0
    private var divideValue = 0

    private var currentMode = Mode.INIT

    private var stack = ArrayDeque<Pair<Int, Int>>()
    override fun sortAndReturnIndex(arrayToSort: Array<Int>, currentIndex: Int): Int
    {
        if (currentMode == Mode.INIT)
        {
            stack.add(Pair(0, arrayToSort.size - 1))
            currentMode = Mode.CHOOSING_DIVIDE_INDEX
        }

        if (currentMode == Mode.CHOOSING_DIVIDE_INDEX)
        {
            if (stack.isEmpty())
                return -1

            val leftAndRight = stack.removeLast()
            if (leftAndRight.first >= leftAndRight.second)
            {
                return currentPosition
            }

            leftIndex = leftAndRight.first
            rightIndex = leftAndRight.second

            divideIndex = leftIndex + (rightIndex - leftIndex).div(2)
            divideValue = arrayToSort[divideIndex]

            currentMode = Mode.SWAPPING_DIVIDE_AND_RIGHT_VALUE

            return divideIndex
        }

        if (currentMode == Mode.SWAPPING_DIVIDE_AND_RIGHT_VALUE)
        {
            swap(arrayToSort, divideIndex, rightIndex)

            currentPosition = leftIndex
            index = leftIndex

            currentMode = Mode.SORTING

            return rightIndex;
        }

        if (currentMode == Mode.SORTING)
        {
            if (index <= rightIndex - 1)
            {
                if (arrayToSort[index] < divideValue)
                {
                    swap(arrayToSort, index, currentPosition)
                    currentPosition++
                }
                index++
                return index
            }
            else
            {
                swap(arrayToSort, currentPosition, rightIndex)

                currentMode = Mode.CHOOSING_DIVIDE_INDEX

                stack.add(Pair(leftIndex, currentPosition - 1))
                stack.add(Pair(currentPosition + 1, rightIndex))

                return currentPosition
            }
        }

        return -1
    }
}