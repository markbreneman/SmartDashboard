-- phpMyAdmin SQL Dump
-- version 4.0.6
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Nov 06, 2013 at 11:00 PM
-- Server version: 5.5.33
-- PHP Version: 5.5.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Database: `freebusy`
--

-- --------------------------------------------------------

--
-- Table structure for table `people`
--

CREATE TABLE `people` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `busy` tinyint(1) DEFAULT NULL,
  `present` tinyint(1) DEFAULT NULL,
  `needs_break` tinyint(1) DEFAULT NULL,
  `last_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `people`
--

INSERT INTO `people` (`user_id`, `name`, `busy`, `present`, `needs_break`, `last_update`) VALUES
(1, 'Nathalie Collins', 1, 0, 0, '2013-11-06 17:25:43'),
(2, 'Nick Remis', 0, 0, 0, '2013-11-05 23:00:26'),
(3, 'Gordon Hui', 1, 0, 0, '2013-11-05 23:00:43');
(4, 'Feild Craddock', 1, 0, 0, '2013-11-05 23:00:43');
(5, 'Marie Bachoc', 1, 0, 0, '2013-11-05 23:00:43');
(6, 'mark breneman', 1, 0, 0, '2013-11-05 23:00:43');

-- --------------------------------------------------------

--
-- Table structure for table `watching`
--

CREATE TABLE `watching` (
  `id` int(11) NOT NULL,
  `watcher_id` int(11) NOT NULL,
  `watched_id` int(11) NOT NULL,
  `last_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
