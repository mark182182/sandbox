package com.example.demo.Models

import javax.persistence.Entity
import javax.persistence.GeneratedValue
import javax.persistence.GenerationType
import javax.persistence.Id

@Entity
data class TaskModel(
        @Id @GeneratedValue(strategy = GenerationType.AUTO)
        val id: Long = 0,
        val content: String,
        val completed: Boolean)