import numpy as np
import cv2

def pixel_to_cam_vector(u, v, camera_matrix, dist_coeffs=None):
    """
    Converts a pixel coordinate to a unit vector in the camera frame.

    Args:
        u (float): The x-coordinate of the pixel.
        v (float): The y-coordinate of the pixel.
        camera_matrix (np.ndarray): The camera matrix.
        dist_coeffs (np.ndarray, optional): The distortion coefficients. Defaults to None.

    Returns:
        np.ndarray: A unit vector in the camera frame.
    """
    # Create a 2D point from the input pixel coordinates
    pixel = np.array([[[u, v]]], dtype=np.float32)

    # Undistort the pixel coordinate to get normalized image coordinates
    normalized_coords = cv2.undistortPoints(pixel, camera_matrix, dist_coeffs)

    # Extract the normalized coordinates
    x_norm = normalized_coords[0, 0, 0]
    y_norm = normalized_coords[0, 0, 1]

    # Create a 3D vector in the camera frame (x, y, 1)
    cam_vector = np.array([x_norm, y_norm, 1.0])

    # Normalize the vector to get a unit vector
    unit_vector = cam_vector / np.linalg.norm(cam_vector)

    return unit_vector
