package com.example.demo.Repository

import com.example.demo.Models.TaskModel
import org.springframework.data.repository.CrudRepository

interface TaskRepository : CrudRepository<TaskModel, Long>