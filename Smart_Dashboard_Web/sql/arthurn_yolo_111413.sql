-- phpMyAdmin SQL Dump
-- version 3.4.11.1
-- http://www.phpmyadmin.net
--
-- Host: db149c.pair.com
-- Generation Time: Nov 14, 2013 at 09:25 PM
-- Server version: 5.5.29
-- PHP Version: 5.3.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `arthurn_yolo`
--

-- --------------------------------------------------------

--
-- Table structure for table `people`
--

CREATE TABLE IF NOT EXISTS `people` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `busy` tinyint(1) DEFAULT NULL,
  `present` tinyint(1) DEFAULT NULL,
  `needs_break` tinyint(1) DEFAULT NULL,
  `last_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `phone` text NOT NULL,
  `location` text NOT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Dumping data for table `people`
--

INSERT INTO `people` (`user_id`, `name`, `busy`, `present`, `needs_break`, `last_update`, `phone`, `location`) VALUES
(1, 'Nathalie Collins', 1, 0, 0, '2013-11-15 02:14:01', '4159370007\r\n', 'San Francisco'),
(2, 'Nick Remis', 0, 0, 0, '2013-11-15 02:14:01', '6088863348\r\n', 'San Francisco'),
(3, 'Gordon Hui', 1, 0, 0, '2013-11-15 02:14:01', '3015265396\r\n', 'New York'),
(4, 'Feild Craddock', 1, 0, 0, '2013-11-15 02:14:01', '8033665105\r\n', 'New York'),
(5, 'Marie Bachoc', 1, 0, 0, '2013-11-15 02:14:01', '3474332172\r\n', 'New York'),
(6, 'mark breneman', 1, 0, 0, '2013-11-15 02:14:01', '7176157555\r\n', 'New York');

-- --------------------------------------------------------

--
-- Table structure for table `watching`
--

CREATE TABLE IF NOT EXISTS `watching` (
  `id` int(11) NOT NULL,
  `watcher_id` int(11) NOT NULL,
  `watched_id` int(11) NOT NULL,
  `last_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
