package com.example.demo.Controllers

import com.example.demo.Models.TaskModel
import com.example.demo.Repository.TaskRepository
import org.springframework.web.bind.annotation.*

@RestController
@RequestMapping("/")
class TaskController(val taskRepository: TaskRepository) {

    @GetMapping("/tasks")
    fun getAllTasks() = taskRepository.findAll()

    @GetMapping("/task/{id}")
    fun getTaskById(@PathVariable id: Long) = taskRepository.findById(id)

    @PutMapping("/task/{id}")
    fun updateTask(@PathVariable id: Long, @RequestBody task: TaskModel) {
        assert(id == task.id)
        taskRepository.save(task)
    }

    @PostMapping("/create_task")
    fun createTask(@RequestBody task: TaskModel) = taskRepository.save(task)

    @DeleteMapping("/task/{id}")
    fun deleteTask(@PathVariable id: Long) = taskRepository.deleteById(id)
}